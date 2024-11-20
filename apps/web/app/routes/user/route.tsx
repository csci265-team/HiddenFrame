/* eslint-disable @typescript-eslint/no-explicit-any */
import type { LoaderFunction, MetaFunction, ActionFunction } from "@remix-run/node";
import { json, redirect } from "@remix-run/node";
import { PageHeader, Button, Input } from "../../components";
import { getSession } from "../../session";
import { Form, useActionData, useNavigation } from "@remix-run/react";
import { useEffect } from "react";
import { BASE_API_URL } from "../../lib/consts";
import { toast } from "sonner";

export const meta: MetaFunction = () => {
    return [
        { title: "HiddenFrame" },
        { name: "description", content: "Welcome to HiddenFrame!" },
    ];
};

export const loader: LoaderFunction = async ({ request }) => {
    const session = await getSession(request.headers.get("Cookie"));
    const username = session.get("username");

    if (!username) return redirect("/login");

    return { username };
};

export const action: ActionFunction = async ({ request }) => {
    const session = await getSession(request.headers.get("Cookie"));
    const token = session.get("token");
    const formData = await request.formData();
    const actionType = formData.get("actionType");

    if (actionType === "changePassword") {
        const newPassword = formData.get("password") as string;
        const confirmPassword = formData.get("confirm-password") as string;

        if (newPassword !== confirmPassword) {
            return json({ success: false, message: "Passwords do not match" }, { status: 400 });
        }

        const resp = await fetch(`${BASE_API_URL}/user`, {
            method: "PATCH",
            body: JSON.stringify({ password: newPassword }),
            headers: {
                "Content-Type": "application/json",
                "Authorization": token || "",
                "Cookie": `token=${token}`,
            }
        });

        if (resp.ok) {
            return json({ success: true, message: "Password changed successfully" }, { status: 200 });
        } else {
            const error = await resp.json();
            return json({ success: false, message: error.message });
        }
    } else if (actionType === "createInvite") {
        const resp = await fetch(`${BASE_API_URL}/invites/create`, {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
                "Authorization": token || "",
                "Cookie": `token=${token}`,
            }
        });

        if (resp.ok) {
            const body = await resp.json();
            return json({ success: true, inviteId: body.inviteId }, { status: 200 });
        } else {
            const error = await resp.json();
            return json({ success: false, message: error.message });
        }
    }

    return json({ success: false, message: "Invalid action" }, { status: 400 });
};

type ActionData = {
    success: boolean;
    message?: string;
    inviteId?: number;
};

export default function Account() {
    const actionData = useActionData<ActionData>();
    const transition = useNavigation();
    const loading = transition.state === "submitting";

    useEffect(() => {
        if (actionData) {
            if (!actionData.success) {
                toast.error(actionData.message || "An error occurred");
            } else {
                toast.success(actionData.message || "Action completed successfully");
            }
        }
    }, [actionData]);

    return (
        <div className="flex items-center justify-center h-full">
            <div className="flex flex-col items-center gap-8 h-full">
                <PageHeader />

                <h2 className="text-2xl font-black ">User Account</h2>

                <div className="flex flex-col gap-4 p-4">
                    <h3 className="text-xl">Change password</h3>
                    <Form method="post" className="flex flex-col gap-4 p-4">
                        <Input type="hidden" name="actionType" value="changePassword" />
                        <Input type="password" id="password" name="password" placeholder="Enter new password" />
                        <Input type="password" id="confirm-password" name="confirm-password" placeholder="Confirm new password" />
                        <Button loading={loading} type="submit">Change Password</Button>
                    </Form>
                </div>

                <div className="flex flex-col gap-4 p-4">
                    <h3 className="text-xl">Invites</h3>
                    <p> You have 1 invite left</p>
                    <ul className="list-disc list-inside">
                        <li>
                            xyzABCAIdio
                        </li>
                        <li>
                            ABCakwfbkwaj
                        </li>
                        <li>
                            235jjkndf8
                        </li>
                        <li>
                            mhawd7awfAJKWD
                        </li>
                    </ul>

                    <Form method="post" className="flex flex-col gap-4 p-4">
                        <Input type="hidden" name="actionType" value="createInvite" />
                        <Button loading={loading} type="submit">Create New Invite</Button>
                    </Form>

                    {actionData?.inviteId && <p>Invite created successfully. Invite ID: {actionData.inviteId}</p>}
                </div>
            </div>
        </div>
    );
}