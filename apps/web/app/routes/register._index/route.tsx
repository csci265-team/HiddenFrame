/* eslint-disable @typescript-eslint/no-explicit-any */
import type { MetaFunction, ActionFunction } from "@remix-run/node";
import { json, redirect } from "@remix-run/node";
import { PageHeader, Button, Input } from "../../components";
import { BASE_API_URL } from "../../lib/consts";
import { useEffect } from "react";
import { useSearchParams, useActionData, Form, useNavigation } from "@remix-run/react";
import { hashPassword } from "../../lib/utils";
import { toast } from "sonner";

export const meta: MetaFunction = () => {
    return [
        { title: "HiddenFrame" },
        { name: "description", content: "Welcome to HiddenFrame!" },
    ];
};

export const action: ActionFunction = async ({ request }) => {
    const formData = await request.formData();
    const inviteId = formData.get("inviteId") as string;
    const username = formData.get("username") as string;
    const password = formData.get("password") as string;

    const hashedPassword = await hashPassword(password);

    const resp = await fetch(`${BASE_API_URL}/register`, {
        method: "POST",
        body: JSON.stringify({
            inviteId,
            username,
            password: hashedPassword,
        }),
        headers: {
            "Content-Type": "application/json",
        }
    });

    if (resp.ok) {
        return redirect("/login");
    } else {
        const error = await resp.text();
        return json({ error }, { status: 400 });
    }
};

export default function Register() {
    const [searchParams] = useSearchParams();
    const inviteId = searchParams.get("inviteId");
    const actionData = useActionData();
    const transition = useNavigation();
    const loading = transition.state === "submitting";

    useEffect(() => {
        // @ts-expect-error cant type
        if (actionData?.error) {
            // @ts-expect-error cant type
            toast.error("Unable to register", { description: actionData.error });
        }
    }, [actionData]);

    return (
        <div className="flex items-center justify-center h-full">
            <div className="flex flex-col items-center gap-8 h-full">
                <PageHeader />

                <h2 className="text-2xl font-black ">Register</h2>

                <div className="flex flex-col gap-4 p-4">
                    <Form method="post" className="flex flex-col gap-4 p-4">
                        <input type="hidden" name="inviteId" value={inviteId || ""} />
                        <Input type="text" id="username" name="username" placeholder="Username" />
                        <Input type="password" id="password" name="password" placeholder="Password" />
                        <Button loading={loading} type="submit">Register</Button>
                    </Form>
                </div>
            </div>
        </div>
    );
}