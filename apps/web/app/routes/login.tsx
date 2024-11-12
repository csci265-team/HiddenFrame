/* eslint-disable @typescript-eslint/no-explicit-any */
import type { MetaFunction, ActionFunction } from "@remix-run/node";
import { json, redirect } from "@remix-run/node";
import { useActionData, Form, useNavigation } from "@remix-run/react";
import { PageHeader, Button, Input } from "../components";
import { BASE_API_URL } from "../lib/consts";
import { hashPassword } from "../lib/utils";

export const meta: MetaFunction = () => {
    return [
        { title: "HiddenFrame" },
        { name: "description", content: "Welcome to HiddenFrame!" },
    ];
};

export const action: ActionFunction = async ({ request }) => {
    const formData = await request.formData();
    const username = formData.get("username") as string;
    const password = formData.get("password") as string;

    const hashedPassword = await hashPassword(password);

    const resp = await fetch(`${BASE_API_URL}/login`, {
        method: "POST",
        body: JSON.stringify({
            username,
            password: hashedPassword
        }),
        headers: {
            "Content-Type": "application/json",
        }
    });

    if (resp.ok) {
        const body = await resp.json();
        return redirect("/", {
            headers: {
                "Set-Cookie": `token=${body.token}; HttpOnly; Path=/`
            }
        });
    } else {
        return json({ error: "Invalid credentials" }, { status: 401 });
    }
};

export default function Login() {
    const actionData = useActionData();
    const transition = useNavigation();
    const loading = transition.state === "submitting";

    return (
        <div className="flex items-center justify-center h-full">
            <div className="flex flex-col items-center gap-8 h-full">
                <PageHeader />

                <h2 className="text-2xl font-black ">Login</h2>

                <div className="flex flex-col gap-4 p-4">
                    <Form method="post" className="flex flex-col gap-4 p-4">
                        <Input type="text" id="username" name="username" placeholder="Username" />
                        <Input type="password" id="password" name="password" placeholder="Password" />
                        <Button loading={loading} type="submit">Login</Button>
                    </Form>
                    { /* @ts-expect-error it only returns error if error otherwise redirects */}
                    {actionData?.error && <p className="text-red-500">{actionData.error}</p>}
                </div>
            </div>
        </div>
    );
}